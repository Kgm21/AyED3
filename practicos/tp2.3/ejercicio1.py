def dibujar_rectangulo(anchura,altura,caracter):
    for i in range(altura):
        for j in range(altura):
            print(caracter, end="")
        print()

anchura = int(input("ingrese la anchura del rectangulo: "))
altura = int(input("ingrese la altura del rectangulo: "))
caracter=input("ingrese el caracter a utilizar en el dibujo: ")

print("Dibujando rectangulo: ")
dibujar_rectangulo(anchura,altura,caracter)