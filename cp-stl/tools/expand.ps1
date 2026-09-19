# Expand project headers into a single submission; no Python dependency.
[CmdletBinding()]
param([Parameter(Mandatory = $true)][string]$Source, [string]$Output)
$ErrorActionPreference = 'Stop'
$repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$libraryRoot = Join-Path $repoRoot 'cp-stl'
$utf8 = [Text.UTF8Encoding]::new($false)
$sourcePath = (Get-Item -LiteralPath $Source).FullName
if (-not $Output) { $Output = Join-Path $repoRoot 'submission.cpp' }
$Output = [IO.Path]::GetFullPath($Output)
if ($Output -eq $sourcePath) { throw 'Output must not overwrite the source file.' }
$active = [Collections.Generic.HashSet[string]]::new([StringComparer]::OrdinalIgnoreCase)

function Expand-File([string]$Path, [bool]$IsHeader) {
    $Path = [IO.Path]::GetFullPath($Path)
    if ($active.Contains($Path)) { return "// recursive include skipped: $([IO.Path]::GetFileName($Path))" }
    [void]$active.Add($Path)
    $result = [Text.StringBuilder]::new()
    if ($IsHeader) {
        # Per-header guards retain correct behavior even across #ifdef branches.
        $sha = [Security.Cryptography.SHA256]::Create()
        try { $digest = [BitConverter]::ToString($sha.ComputeHash($utf8.GetBytes($Path.ToLowerInvariant()))).Replace('-', '') }
        finally { $sha.Dispose() }
        $guard = 'CP_EXPANDED_' + $digest
        [void]$result.AppendLine("#ifndef $guard")
        [void]$result.AppendLine("#define $guard")
    }
    foreach ($line in [IO.File]::ReadAllLines($Path, $utf8)) {
        if ($line -match '^\s*#\s*pragma\s+once\s*$') { continue }
        if ($line -match '^\s*#\s*include\s*([<"])([^>"]+)[>"]') {
            $kind = $Matches[1]
            $name = $Matches[2]
            if ($kind -eq '"' -or $name.StartsWith('atcoder/')) {
                $candidates = @(
                    (Join-Path (Split-Path -Parent $Path) $name),
                    (Join-Path $libraryRoot $name),
                    (Join-Path (Join-Path $repoRoot 'ac-library') $name)
                )
                $includePath = $null
                foreach ($candidate in $candidates) {
                    if (Test-Path -LiteralPath $candidate -PathType Leaf) { $includePath = $candidate; break }
                }
                if (-not $includePath) { throw "Cannot expand header '$name' included by '$Path'." }
                [void]$result.AppendLine((Expand-File $includePath $true))
                continue
            }
        }
        [void]$result.AppendLine($line)
    }
    if ($IsHeader) { [void]$result.AppendLine("#endif // $guard") }
    [void]$active.Remove($Path)
    return $result.ToString()
}
$text = Expand-File $sourcePath $false
[IO.Directory]::CreateDirectory([IO.Path]::GetDirectoryName($Output)) | Out-Null
[IO.File]::WriteAllText($Output, $text, $utf8)
Write-Host ("Exported: " + $Output)
