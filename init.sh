if [ ! -d obj ]; then
    mkdir obj
    echo "Made folder obj/"
fi

if [ ! -d bin ]; then
    mkdir bin
    echo "Made folder bin/"
fi

echo "You can now run make !"