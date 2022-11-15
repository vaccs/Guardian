set -ev
for file in `find dot -name '*.dot' | sort -V`
do
	out=/tmp/${file/dot}.svg
	if [ '(' '!' -e ${out} ')' -o '(' ${file} -nt ${out} ')' ]
	then
		echo "rebuilding ${out}"
		dot -Tsvg < ${file} > ${out}
	fi
done
