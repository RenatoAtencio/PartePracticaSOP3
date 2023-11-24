import os
import sys
import re

# Leo el path y el nombre del archivo pasado por la consola
pathRawFiles = "../Trabajo5/data/Files/RawFiles"
fileName = sys.argv[1]

# Abro el archivo y lo guardo en contenido
with open(os.path.join(pathRawFiles, fileName),'r') as file:
    contenido = file.read()

# Limpio el archivo de caracteres no alfabetico (Algunos caracteres especiales si se mantienen)
contenidoLimpio = re.sub(r'\W+', ' ', contenido).lower()

# Creo el archivo de salida y lo guardo en Files/ProcessedFiles
pathProcessedFiles = "../Trabajo5/data/Files/ProcessedFiles"
processedFileName = 'processed_' + fileName

# Crea y escribe en el archivo de salida si NO existe
if not os.path.exists(os.path.join(pathProcessedFiles,processedFileName)):
    outputFile = open(os.path.join(pathProcessedFiles,processedFileName),'w')
    outputFile.write(contenidoLimpio)
    outputFile.close()