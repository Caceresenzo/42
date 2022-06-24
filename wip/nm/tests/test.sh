export LC_COLLATE=C

echo "Running: $@" 1>&2

nm $@ >/tmp/nm.output 2>&1
nm_exit=$?

./ft_nm $@ >/tmp/ft_nm.output 2>&1
ft_nm_exit=$?

cat /tmp/nm.output | sed 's/nm:/PROGRAM:/g' > /tmp/nm.anonimized.output
cat /tmp/ft_nm.output | sed 's/ft_nm:/PROGRAM:/g' > /tmp/ft_nm.anonimized.output

#if ! diff --color --side-by-side /tmp/ft_nm.anonimized.output /tmp/nm.anonimized.output; then
if ! diff --color --side-by-side --suppress-common-lines /tmp/ft_nm.anonimized.output /tmp/nm.anonimized.output; then
	echo DIFF
	exit 1
fi

if ! test "$nm_exit" = "$ft_nm_exit"; then
	echo EXIT "$nm_exit" != "$ft_nm_exit"
	exit 1
fi
