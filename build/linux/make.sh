mkdir -p release/bin release/share/pdf-presenter
g++ `wx-config --cppflags` -I /usr/include/poppler -I /usr/include/poppler/splash -I /usr/include/glib-2.0/glib `pkg-config --cflags glib-2.0` ../../src/*.cpp -o release/bin/pdf-presenter `wx-config --libs` -lpoppler
cp ../../res/icons/* release/share/pdf-presenter
