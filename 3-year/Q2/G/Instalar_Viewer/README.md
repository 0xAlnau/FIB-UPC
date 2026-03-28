# Com instal·lar Viewer per Gràfics
## Missatge del Racó:
Al laboratori de G usem un visualitzador bàsic (GLarena). A les aules informàtiques, el podeu executar fent:

   ~/assig/grau-g/Viewer/GLarenaSL

Si volueu treballar amb el viewer (GLarena) fora dels laboratoris, el podeu instal·lar en una màquina amb linux, windows i MacOs.

Si per qualsevol motiu haguèssiu de fer els controls de forma no presencial, us serà imprescindible tenir el viewer instal·lat a casa. Per tant, és molt recomanable que l'instal·leu durant les primeres setmanes de curs.

A. Instal.lació en Ubuntu
--------------------------------------

1. Instal.lar requeriments previs de Qt, OpenGL i GLU:

  `sudo apt-get install build-essential libgl1-mesa-dev libglu1-mesa-dev`

2. Descarregar Qt 5 o bé Qt 6

La darrera versió del viewer és compatible amb Qt5 (>=Qt5.15) i Qt6 (>=Qt6.7).

Recomanació:
  - Si ja teniu instal·lada Qt5.15, useu aquesta versió.
  - Si el vostre Ubuntu usa Wayland en comptes de X11 (ho podeu saber fent "echo $XDG_SESSION_TYPE"), millor useu Qt5.15 (sembla que un bug del Wayland amb Qt6 fa que sigui imprescindible que el FS escrigui fragments amb opacitat 1; altrament el resultat no serà l'esperat).
 - Si no teniu Qt, o bé el vostre Ubuntu no usa Wayland, podeu triar indistintament Qt5.15 o Qt6.7+.


  https://www.qt.io/download-qt-installer-oss
  Qt online installer for linux (*)
  (*) Nota amb Qt5: és possible que necessiteu activar la casella "Archive" i tornar al filtrar per veure algunes versions de Qt5, veure figura adjunta.

3. Instal.lar Qt (canvieu el que calgui segons la versió que hagueu descarregat)

`chmod +x qt-unified-linux-x64-3.0.6-online.run; sudo ./qt-unified-linux-x64-3.0.6-online.run`

Si en executar la comanda dona error per carregar les llibreries libxcb-xinerama0 o libxcb-cursor0, s'han d'instal·lar les dependències:

`sudo apt install libxcb-xinerama0 libxcb-cursor0`

Completar la instal.lació:
    Registrar-se i entrar amb un compte de Qt.
    Folder: /opt/Qt
    Components: seleccionar una versió a instal.lar (exemple: 5.15.1)

 Opcional: editar ~/.bashrc i afegir la linia (5.15.1 és un exemple)

       `alias qmake-qt5='/opt/Qt/5.15.1/gcc_64/bin/qmake`

4. Descarregar i descomprimir la darrera versió del viewer.

  http://www.cs.upc.edu/~virtual/G/index.php?dir=2.%20Laboratori/viewer

  (ex. 2025-12-05/)
  tar -xzvf...

5. Descarregar models, textures i fitxers de test:

  http://www.cs.upc.edu/~virtual/G/index.php?dir=2.%20Laboratori/viewer/
   -> models.tgz
   -> tests.tgz
   -> Textures.tgz

 Descomprimir els fitxers anteriors (models, textures i tests), en els directoris

   /assig/grau-g/models
   /assig/grau-g/tests
   /assig/grau-g/Textures

o bé penjant de NewViewer_******:

   NewViewer_*******/models
   NewViewer_*******/tests
   NewViewer_*******/Textures

Nota: la versions més actualitzades dels models, tests i textures les podeu copiar (ex. tar) directament dels laboratoris de la FIB ~/assig/grau-g/{models, Textures, tests}


6. Compilar el viewer

  cd NewViewer_*******   ## (el codi pot variar segons la versió)
  qmake6                 ## o qmake-qt5 segons la versió
  make -j

7. Executar viewer

  ./GLarenaSL (per provar shaders; primera part del curs)
  ./GLarenaPL (per provar plugins; segona part del curs)
