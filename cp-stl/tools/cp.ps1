# Windows PowerShell 5.1+; keep this script ASCII so -File works without a BOM.
[CmdletBinding()]
param(
    [ValidateSet('Build', 'Run', 'Test', 'Export', 'Doctor')]
    [string]$Action = 'Run',
    [string]$Source,
    [string]$InputFile,
    [ValidateSet('Debug', 'Release')]
    [string]$Mode = 'Release',
    [string]$Compiler,
    [string]$Standard = 'c++20'
)
$ErrorActionPreference = 'Stop'
$repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$libraryRoot = Join-Path $repoRoot 'cp-stl'
$utf8 = [Text.UTF8Encoding]::new($false)
[Console]::InputEncoding = $utf8
[Console]::OutputEncoding = $utf8
$OutputEncoding = $utf8
# Native processes also need the console code page, particularly GDB.
if ($env:OS -eq 'Windows_NT') { & "$env:SystemRoot\System32\chcp.com" 65001 | Out-Null }

function Resolve-InputPath([string]$Path) {
    if ([string]::IsNullOrWhiteSpace($Path)) { throw 'A source file is required. Open and save a .cpp file first.' }
    if (-not [IO.Path]::IsPathRooted($Path)) { $Path = Join-Path $repoRoot $Path }
    return (Get-Item -LiteralPath $Path -ErrorAction Stop).FullName
}

try {
    if ($Action -eq 'Export') {
        $sourcePath = Resolve-InputPath $Source
        & (Join-Path $PSScriptRoot 'expand.ps1') -Source $sourcePath
        exit 0
    }
    if (-not $Compiler) {
        $found = Get-Command g++.exe -ErrorAction SilentlyContinue
        if ($found) { $Compiler = $found.Source }
        elseif (Test-Path -LiteralPath 'C:\msys64\ucrt64\bin\g++.exe') { $Compiler = 'C:\msys64\ucrt64\bin\g++.exe' }
        else { throw 'g++ not found. Install MSYS2 UCRT64 or pass -Compiler C:\path\to\g++.exe.' }
    }
    $Compiler = Resolve-InputPath $Compiler
    $compilerDirectory = Split-Path -Parent $Compiler
    # Use DLLs from the same toolchain even if the inherited PATH is stale.
    $env:PATH = $compilerDirectory + ';' + $env:PATH
    if ($Action -eq 'Doctor') {
        Write-Host ("Compiler: " + $Compiler)
        & $Compiler --version
        if ($LASTEXITCODE -ne 0) { throw 'Compiler could not start.' }
        $debugger = Join-Path $compilerDirectory 'gdb.exe'
        if (Test-Path -LiteralPath $debugger) {
            Write-Host ("Debugger: " + $debugger)
            & $debugger --version
            if ($LASTEXITCODE -ne 0) { throw 'Debugger could not start.' }
        } else { throw 'gdb.exe is missing next to the selected compiler.' }
        Write-Host ("Workspace: " + $repoRoot)
        Write-Host ("Standard: " + $Standard)
        exit 0
    }
    if ($Action -eq 'Test') {
        $Source = Join-Path $libraryRoot 'tests\algorithms.cpp'
        $Mode = 'Debug'
    }
    $sourcePath = Resolve-InputPath $Source
    if ([IO.Path]::GetExtension($sourcePath) -notin @('.cpp', '.cc', '.cxx')) {
        throw 'Select a .cpp/.cc/.cxx file with main(); headers are copied or included, not run directly.'
    }
    $resolvedInput = $null
    if ($InputFile) { $resolvedInput = Resolve-InputPath $InputFile }
    $buildDirectory = Join-Path $repoRoot ('.build\' + $Mode.ToLowerInvariant())
    [IO.Directory]::CreateDirectory($buildDirectory) | Out-Null
    $executable = Join-Path $buildDirectory 'program.exe'
    # Remove an old binary first so a failed build can never run stale code.
    if (Test-Path -LiteralPath $executable) { Remove-Item -LiteralPath $executable -Force }
    $compilerArgs = @(
        ('-std=' + $Standard), '-Wall', '-Wextra', '-Wshadow',
        '-finput-charset=UTF-8', '-fexec-charset=UTF-8',
        '-DLOCAL', '-D_GLIBCXX_ASSERTIONS',
        '-I', $libraryRoot, '-I', (Join-Path $repoRoot 'ac-library')
    )
    if ($Mode -eq 'Debug') {
        $compilerArgs += @('-Og', '-g3')
        # GDB may fail to open UTF-8 names in DWARF on a CP936 Windows system.
        # Compile the original file, but map its debug filename to an ASCII mirror.
        # launch.json maps that mirror back to the original editor file.
        $debugSource = Join-Path $buildDirectory 'main.cpp'
        [IO.File]::Copy($sourcePath, $debugSource, $true)
        $compilerArgs += ('-fdebug-prefix-map=' + $sourcePath + '=' + $debugSource)
        $compilerArgs += ('-fdebug-prefix-map=' + $sourcePath.Replace('\', '/') + '=' + $debugSource.Replace('\', '/'))
    }
    else { $compilerArgs += @('-O2', '-g') }
    # Each path is one native argument. Do not concatenate a shell command.
    $compilerArgs += @($sourcePath, '-o', 'program.exe')
    Write-Host ("Compiling: " + $sourcePath)
    # Some Windows linkers cannot open a UTF-8 absolute output path. A relative
    # ASCII output name works even when the workspace itself contains Chinese.
    Push-Location -LiteralPath $buildDirectory
    try {
        & $Compiler @compilerArgs
        $compileExit = $LASTEXITCODE
    } finally { Pop-Location }
    if ($compileExit -ne 0) {
        if (Test-Path -LiteralPath $executable) { Remove-Item -LiteralPath $executable -Force }
        exit $compileExit
    }
    if ($Action -eq 'Build') {
        Write-Host ("Built: " + $executable)
        exit 0
    }
    # Relative files in solutions are always resolved from the repository root.
    Push-Location -LiteralPath $repoRoot
    try {
        if ($resolvedInput) {
            # Raw byte stdin redirection: no PowerShell '<', no UTF-16 pipeline conversion.
            $start = [Diagnostics.ProcessStartInfo]::new()
            $start.FileName = $executable
            $start.WorkingDirectory = $repoRoot
            $start.UseShellExecute = $false
            $start.RedirectStandardInput = $true
            $process = [Diagnostics.Process]::Start($start)
            $stream = [IO.File]::OpenRead($resolvedInput)
            try {
                try { $stream.CopyTo($process.StandardInput.BaseStream) }
                catch [IO.IOException] {
                    # A solution may intentionally stop reading before EOF.
                    $process.WaitForExit()
                    if ($process.ExitCode -eq 0) { Write-Warning 'Program stopped before consuming all input.' }
                }
            } finally {
                $stream.Dispose()
                try { $process.StandardInput.Close() } catch [IO.IOException] {}
            }
            $process.WaitForExit()
            $runExit = $process.ExitCode
            $process.Dispose()
        } else {
            & $executable
            $runExit = $LASTEXITCODE
        }
    } finally { Pop-Location }
    exit $runExit
} catch {
    Write-Error $_ -ErrorAction Continue
    exit 1
}
