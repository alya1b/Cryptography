import random

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        gcd, x, y = extended_gcd(b % a, a)
        return gcd, y - (b // a) * x, x

def encrypt(message, public_key):
    e, N = public_key
    encrypted_msg = pow(message, e, N)
    return encrypted_msg

def decrypt(encrypted_msg, private_key):
    d, N = private_key
    decrypted_msg = pow(encrypted_msg, d, N)
    return decrypted_msg

# Параметри RSA
p = 11
q = 5
e = 7
m = 22

# Обчислення модуля N та значення функції Ейлера
N = p * q
phi = (p - 1) * (q - 1)

# Перевірка взаємної простоти з phi
g = gcd(e, phi)
if g != 1:
    raise ValueError("Помилка: e не взаємно просте з φ(N).")

# Обчислення приватного ключа d за допомогою оберненого елемента
d = extended_gcd(e, phi)[1]
d = (d % phi + phi) % phi

# Публічний та приватний ключі
public_key = (e, N)
private_key = (d, N)

print("Параметри RSA:")
print("p =", p)
print("q =", q)
print("e =", e)
print("m (повідомлення) =", m)
print("")

print("1. Генерація ключів:")
print("Обчислення модуля N:")
print("N = p * q =", p, "*", q, "=", N)
print("Обчислення значення функції Ейлера:")
print("φ(N) = (p - 1) * (q - 1) =", (p - 1), "*", (q - 1), "=", phi)
print("Вибір відкритого ключа e:")
print("e =", e)
print("Перевірка взаємної простоти з φ(N):")
print("gcd(e, φ(N)) =", gcd(e, phi))
print("Обчислення приватного ключа d за допомогою оберненого елемента:")
print("d =", d)
print("")

print("2. Шифрування повідомлення (m):")
print("Шифрування за формулою c ≡ m^e (mod N):")
encrypted_message = encrypt(m, public_key)
print("c ≡", m, "^", e, "(mod", N, ") =", encrypted_message)
print("Зашифроване повідомлення (c):", encrypted_message)
print("")

print("3. Розшифрування повідомлення (c):")
print("Розшифрування за формулою m ≡ c^d (mod N):")
decrypted_message = decrypt(encrypted_message, private_key)
print("m ≡", encrypted_message, "^", d, "(mod", N, ") =", decrypted_message)
print("Розшифроване повідомлення (m):", decrypted_message)
