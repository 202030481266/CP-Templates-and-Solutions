import math

def modInverse_fermat(a, p):
  """
  使用费马小定理计算 a 关于质数 p 的模逆元。

  Args:
    a: 目标整数。
    p: 质数模数。

  Returns:
    a 关于模 p 的逆元 (一个 1 到 p-1 之间的整数)。
    如果 p 不是质数或 a 是 p 的倍数，结果未定义（或可能出错）。
    如果 a 是 p 的倍数 (a % p == 0)，则逆元不存在，返回 None。
  Raises:
    ValueError: 如果 p 不是大于 1 的整数。
  """
  if not isinstance(p, int) or p <= 1:
    raise ValueError("模数 p 必须是大于 1 的整数。")
  # 费马小定理要求 p 是质数，这里我们假设调用者确保了这一点。
  # 如果需要，可以添加素性测试，但这会增加计算成本。

  # 标准化 a 到 [0, p-1] 范围内
  a = a % p

  # 如果 a 是 p 的倍数，则逆元不存在
  if a == 0:
    print(f"错误：{a // p * p} (即 0 mod {p}) 没有模 {p} 的逆元。")
    return None

  # 计算 a^(p-2) % p
  # pow(a, p - 2, p) 使用高效的模幂算法
  inverse = pow(a, p - 2, p)
  return inverse

# --- 示例 ---
a = 3
p = 11 # 11 是一个质数

inverse = modInverse_fermat(a, p)

if inverse is not None:
  print(f"数字 {a} 关于质数模 {p} 的逆元是: {inverse}")
  # 验证: (a * inverse) % p 应该等于 1
  print(f"验证: ({a} * {inverse}) % {p} = {(a * inverse) % p}")
else:
  print(f"数字 {a} 关于模 {p} 的逆元不存在。")

print("-" * 20)

a = 10
p = 17 # 17 是一个质数
inverse = modInverse_fermat(a, p)
if inverse is not None:
  print(f"数字 {a} 关于质数模 {p} 的逆元是: {inverse}")
  print(f"验证: ({a} * {inverse}) % {p} = {(a * inverse) % p}")
else:
  print(f"数字 {a} 关于模 {p} 的逆元不存在。")

print("-" * 20)

# 尝试一个 a 是 p 的倍数的例子
a = 22
p = 11
inverse = modInverse_fermat(a, p)
# 输出会提示错误，并返回 None

# --- 更通用的方法：扩展欧几里得算法 (可选) ---
# 这个方法不要求 p 是质数，只要 a 和 p 互质即可

def extended_gcd(a, b):
  """
  计算 ax + by = gcd(a, b) 的解 (gcd, x, y)。
  """
  if a == 0:
    return (b, 0, 1)
  else:
    gcd, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return (gcd, x, y)

def modInverse_eea(a, m):
  """
  使用扩展欧几里得算法计算 a 关于模数 m 的逆元。
  m 不必是质数。
  """
  if not isinstance(m, int) or m <= 1:
      raise ValueError("模数 m 必须是大于 1 的整数。")

  a = a % m
  if a == 0:
      print(f"错误：0 没有模 {m} 的逆元。")
      return None

  gcd, x, y = extended_gcd(a, m)

  if gcd != 1:
    # a 和 m 不互质，逆元不存在
    print(f"错误：{a} 和 {m} 不互质 (gcd={gcd})，逆元不存在。")
    return None
  else:
    # x 可能为负数，需要转换到 [1, m-1] 范围内
    # (x % m + m) % m 是一种确保结果为正的标准方法
    return (x % m + m) % m

print("-" * 20)
print("使用扩展欧几里得算法:")
a = 3
p = 11 # 质数
inverse_eea = modInverse_eea(a, p)
if inverse_eea is not None:
    print(f"(EAA) 数字 {a} 关于模 {p} 的逆元是: {inverse_eea}")
    print(f"验证: ({a} * {inverse_eea}) % {p} = {(a * inverse_eea) % p}")

a = 10
m = 26 # 非质数，但 a 和 m 互质 (gcd=2) -> 错误，gcd(10, 26) = 2，不存在
print("-" * 20)
inverse_eea = modInverse_eea(a, m)
if inverse_eea is not None:
    print(f"(EAA) 数字 {a} 关于模 {m} 的逆元是: {inverse_eea}")
else:
    print(f"(EAA) 数字 {a} 关于模 {m} 的逆元不存在。")


a = 7
m = 26 # 非质数, gcd(7, 26)=1, 存在
print("-" * 20)
inverse_eea = modInverse_eea(a, m)
if inverse_eea is not None:
    print(f"(EAA) 数字 {a} 关于模 {m} 的逆元是: {inverse_eea}") # 7 * 15 = 105 = 4 * 26 + 1
    print(f"验证: ({a} * {inverse_eea}) % {m} = {(a * inverse_eea) % m}")
else:
    print(f"(EAA) 数字 {a} 关于模 {m} 的逆元不存在。")