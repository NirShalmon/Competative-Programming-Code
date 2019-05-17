find . -name *.c* -exec printf "cat header.txt \"{}\" > \"{}.tmp\";mv \"{}.tmp\" \"{}\";" > commands.sh ';'
chmod +x commands.sh
./commands.sh
rm commands.sh
