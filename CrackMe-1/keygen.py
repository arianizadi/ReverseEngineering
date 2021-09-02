import string
import random

finalKey = ""
significantChar = random.choice(string.ascii_letters)
finalKey += significantChar
for i in range(8):
    finalKey += random.choice(string.ascii_letters)
finalKey += significantChar

print("Key -> " + finalKey)
