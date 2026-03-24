import os
import re
import pandas as pd

# =========================================================
# CONFIGURACIÓN
# =========================================================

# Carpeta donde están los archivos salidaX.txt
# (usar ruta relativa dentro del repositorio)
carpeta = "raw_output_example"

# Número de archivos a procesar
num_archivos = 100

# Límite de datos (para control computacional)
limite_datos = 33030000

# =========================================================
# EXTRACCIÓN DE ENERGÍA DEPOSITADA
# =========================================================

# Patrón para extraer las energías depositadas
patron = re.compile(r"G4WT\d > Deposited energy: (\d+\.\d+|\d+)")

energias = []

print("Extrayendo energías depositadas...")

for i in range(1, num_archivos + 1):
    archivo = os.path.join(carpeta, f"salida{i}.txt")

    if os.path.exists(archivo):
        with open(archivo, "r") as f:
            for linea in f:
                match = patron.search(linea)
                if match:
                    energias.append(float(match.group(1)))

# Guardar CSV completo
df = pd.DataFrame(energias, columns=["Energia_Depositada"])
df.to_csv("energias_depositadas.csv", index=False)

print(f"Total de valores extraídos: {len(df)}")
print("Archivo guardado: energias_depositadas.csv")

# =========================================================
# LIMITAR DATOS (OPCIONAL)
# =========================================================

df_limitado = df.iloc[:limite_datos]
df_limitado.to_csv("energias_depositadas_limite.csv", index=False)

print(f"Datos limitados a {len(df_limitado)} valores")
print("Archivo guardado: energias_depositadas_limite.csv")

# =========================================================
# FILTRADO (ELIMINAR CEROS)
# =========================================================

df_filtrado = df_limitado[df_limitado["Energia_Depositada"] != 0]
df_filtrado.to_csv("energias_depositadas_limite_filtrado.csv", index=False)

num_eliminados = len(df_limitado) - len(df_filtrado)

print("Filtrado completado:")
print(f"Valores eliminados (energía = 0): {num_eliminados}")
print(f"Valores finales: {len(df_filtrado)}")
print("Archivo guardado: energias_depositadas_limite_filtrado.csv")
