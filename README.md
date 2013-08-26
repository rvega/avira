# Instalación Interactiva Avira

## Links importantes

* [Tareas](https://github.com/rvega/avira/issues)
* [Archivos](https://drive.google.com/folderview?id=0BzkxuvucQigbMDh4bEprcS1NNHc&usp=sharing)

## Instalar y compilar OF desde git.

1. Primero, cree su repositorio local, baje los submódulos de git y instale OF. Mas info sobre [git](http://www.codeschool.com/courses/try-git) y [submódulos](http://git-scm.com/book/en/Git-Tools-Submodules).

        git clone https://github.com/rvega/avira.git repo
        cd repo
        git submodule update --init --recursive
        cd openFrameworks/scripts/linux/ubuntu
        sudo ./install_dependencies.sh
        sudo ./install_codeblocks.sh
        sudo ./install_codecs.sh

2. En el directorio openFrameworks/ está la versión 0.7.4 de openFrameworks, fue bajado del repositorio de git de OF entonces no trae los proyectos de CodeBlocks ni Xcode ni Makefile para los ejemplos. Si los quiere generar:

        cd openFrameworks/apps/devApps/projectGenerator 
        make
        cd bin
        ./projectGenerator

    En la columna "generate examples" escoja el formato de proyecto que le interese (linux 64 en mi caso) y luego haga click en "&lt;--Generate"
  
## Subdirectorios para cada tarea.

Inicialmente, las tareas técnicas que tenemos son independientes una de otra, para facilidad de desarrollo, hagamos un proyecto para trabajar en cada una de ellas. Por ejemplo, crear un proyecto para la tarea "entenderCarpetas".
    
1. Abrir el ProjectGenerator:

        cd openFrameworks/projectGenerator
        ./projectGenerator
    
2. Cambiar "name" a "EntenderCarpetas".
3. Cambiar "path" a "repo/EntenderCarpetas"
4. Agregar Addons necessarios.
5. Click en "Generate Project"
