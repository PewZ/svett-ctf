from pwn import *

r = remote("localhost", 8000)

def get_coin(line):
	words = line.split()
	coin = words[0][1:]
	coin = round((float(coin) * 100), 2)
	coin = int(coin)
	return coin

data = r.recvline()
coin = get_coin(data)

data = r.recvuntil("bills:")
words = data.split()
value = words[0][1:]
value = float(value.replace(',',''))*100
value = int(value)

while True:

	if value > coin:
		r.sendline('0')

	elif value <= coin:
		amount = coin / value
		coin = coin - (amount*value)
		r.sendline(str(amount))

	if coin == 0 and value == 1:
		line = r.recvline()
		line = r.recvline()

		if "$" in line:
			coin = get_coin(line)
		else: 
			print line
			r.interactive()
			break
	
	data = r.recvuntil(":")
	words = data.split()

	if words[0][0] == '$':
		value = words[0][1:]
		value = float(value.replace(',', ''))*100
		value = int(value)
	else:
		value = words[1][1:-3]
		value = int(value)

r.interactive()

