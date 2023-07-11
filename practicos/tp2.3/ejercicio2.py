anio= int(input("Ingrese un año: "))

def es_bisiesto(anio):
    if (anio % 4 == 0) and (anio % 100 != 0 or anio % 400 == 0):
         return True
    else: 
         return False


if es_bisiesto(anio):
     print(anio," es bisiesto. ")
else: 
     print(anio, "no es bisiesto. ")