# PracAOC - Proyecto de Arquitectura de Ordenadores y Computadores

Un proyecto de procesamiento de imágenes desarrollado en C++ con Qt que implementa algoritmos de visión por computador utilizando ensamblador inline para optimización de rendimiento. El proyecto está enfocado en el reconocimiento de matrículas de vehículos.

## 📋 Descripción

Este proyecto implementa un sistema de procesamiento de imágenes para el análisis y reconocimiento de caracteres en matrículas. Utiliza técnicas avanzadas de procesamiento de imágenes y está optimizado con código ensamblador para máximo rendimiento.

## 🚀 Características

- **Procesamiento de imágenes** con funciones básicas (copiar, borrar, invertir, umbralizar)
- **Eliminación de ruido** con filtros especializados
- **Detección de líneas verticales y horizontales** para segmentación
- **Recorte inteligente** de regiones de interés
- **Reconocimiento de caracteres** mediante matching de patrones
- **Interfaz gráfica** desarrollada con Qt
- **Optimización con ensamblador** para operaciones críticas

## 🛠️ Tecnologías Utilizadas

- **C++** - Lenguaje de programación principal
- **Qt Framework** - Interfaz gráfica y manejo de imágenes
- **Ensamblador x86-64** - Optimización de algoritmos críticos
- **QMake** - Sistema de construcción

## 📁 Estructura del Proyecto

```
pracaoc/
├── imageprocess.cpp    # Implementación de algoritmos de procesamiento
├── imageprocess.h      # Definiciones de funciones de procesamiento
├── pracaoc.cpp         # Lógica principal de la aplicación
├── pracaoc.h           # Definiciones de la clase principal
├── main.cpp            # Punto de entrada de la aplicación
├── mainForm.ui         # Interfaz gráfica en Qt Designer
├── pracaoc.pro         # Archivo de proyecto QMake
└── letras/             # Dataset de caracteres de referencia
    ├── 0.jpg - 9.jpg   # Dígitos del 0 al 9
    └── A.jpg - Z.jpg   # Letras del alfabeto

matriculas/             # Conjunto de imágenes de prueba
└── M1.jpg - M50.jpg    # Imágenes de matrículas para testing
```

## ⚙️ Funciones Principales

### Procesamiento Básico
- `copiar()` - Copia de imágenes en memoria
- `borrar()` - Inicialización de buffers de imagen
- `invertir()` - Inversión de valores de píxeles
- `umbralizar()` - Binarización de imágenes

### Análisis y Detección
- `detectarV_min()` / `detectarV_max()` - Detección de límites verticales
- `detectarH_F1()` / `detectarH_F2()` - Detección de líneas horizontales
- `recortar()` - Extracción de regiones de interés
- `matching()` - Reconocimiento de caracteres por correlación

### Filtrado
- `eliminarRuido_F1()` / `eliminarRuido_F2()` - Filtros de eliminación de ruido

## 🔧 Instalación y Compilación

### Prerrequisitos
- Qt 5.x o superior
- Compilador C++ compatible (GCC/Clang)
- QMake

### Pasos de instalación

1. **Clonar el repositorio**
```bash
git clone https://github.com/CCamberoR/pracaoc-image-processing.git
cd "Proyecto AOC"
```

2. **Generar Makefile**
```bash
cd pracaoc
qmake pracaoc.pro
```

3. **Compilar**
```bash
make
```

4. **Ejecutar**
```bash
./pracAOC
```

## 📊 Uso

1. **Cargar imagen**: Selecciona una imagen de matrícula desde el menú
2. **Preprocesamiento**: Aplica filtros de umbralización y eliminación de ruido
3. **Detección**: El sistema detecta automáticamente los caracteres
4. **Reconocimiento**: Cada caracter es comparado con el dataset de referencia
5. **Resultado**: Se muestra la matrícula reconocida

## 🧪 Testing

El proyecto incluye un conjunto de 50 imágenes de prueba en la carpeta `matriculas/`. Estas imágenes cubren diferentes condiciones de iluminación, ángulos y tipos de matrículas.

## 🎯 Optimizaciones

- **Ensamblador inline**: Las funciones críticas están implementadas en ensamblador x86-64 para máximo rendimiento
- **Gestión de memoria**: Uso eficiente de punteros y acceso directo a memoria
- **Algoritmos optimizados**: Loops desenrollados y uso eficiente de registros

## 📝 Licencia

Este programa es software libre bajo la Licencia Pública General GNU versión 2. Ver el encabezado de los archivos fuente para más detalles.

---

*Desarrollado como parte del curso de Arquitectura de Ordenadores y Computadores*
