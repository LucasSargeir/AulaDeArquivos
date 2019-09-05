import struct
import sys

def tamanhoArquivo(f):
	f.seek(0,2)
	c = f.tell()
	f.seek(0)
	return c

def buscaBinaria(f,bCep,ini,fim,counter):

	registroCEP = struct.Struct("72s72s72s72s2s8s2s")
	cepColumn = 5
	meio = 0
	f.seek(0)

	if(ini <= fim):

		meio = int((ini+fim)//2)

		f.seek(meio*registroCEP.size)
		line = f.read(registroCEP.size);
		counter +=1
		record = registroCEP.unpack(line)					# Pega a linha no formato da estrutura
		cep = str(record[cepColumn])	
		
		if( bCep == cep ):
			print("Logradouro:",str(record[0]))
			print("Bairro:",str(record[1]))
			print("Cidade:",str(record[2]))
			print("UF:",str(record[3]))
			print("Sigla:",str(record[4]))
			print("CEP:",str(record[5]))
			print ("\nTotal de Registros Lidos: %d\n" % counter)
			return counter
		
		else:
			if(bCep > cep):
				buscaBinaria(f,bCep,meio+1,fim,counter)
			
			elif(bCep < cep):
				buscaBinaria(f,bCep,ini,meio-1,counter)

	else:
		print("Nao foi possivel encontrar o CEP\n")
		return counter

#_______________________________[main()]_______________________________

bCep = ""

if(len(sys.argv) != 2):
	print ("USO %s [CEP]" % sys.argv[0])
	#s = str(input("Entre com o CEP desejado: "))
	#bCep = bCep.decode('latin1')
	quit()
	bCep = str("b'"+s+"'")
	#bCep = bCep.encode('latin1')

else:
	bCep = sys.argv[1].decode('latin1')



registroCEP = struct.Struct("72s72s72s72s2s8s2s")
cepColumn = 5											# Em qual coluna esta o CEP
f = open("cep_ordenado.dat","rb")

print("\n__________________________[INFO]_________________________\n\n")
print ("Tamanho do Arquivo: %d" % tamanhoArquivo(f))
print ("Tamanho da Estrutura: %d" % registroCEP.size)
print ("Tamanho do Arquivo em Registros: %d\n" % (int(tamanhoArquivo(f))/int(registroCEP.size)))


print("\n_____________________[BUSCA BINARIA]_____________________\n\n")
fim  = tamanhoArquivo(f)/registroCEP.size

counter = buscaBinaria(f,bCep,0,fim,0)


print("___________________[BUSCA NAO BINARIA]___________________\n\n")

f.seek(0)
line = f.read(registroCEP.size)
counter = 1

while(len(line) == registroCEP.size):

	record = registroCEP.unpack(line)					# Pega a linha no formato da estrutura
	cep = str(record[cepColumn])						# Pega o CEP da estrutura
	
	if(cep == bCep):
		print("Logradouro:",str(record[0]))
		print("Bairro:",str(record[1]))
		print("Cidade:",str(record[2]))
		print("UF:",str(record[3]))
		print("Sigla:",str(record[4]))
		print("CEP:",str(record[5]))
		break

	counter += 1
	line = f.read(registroCEP.size)

print ("\nTotal de Registros Lidos: %d\n" % counter)

f.close()