export LC_COLLATE=C

echo "Running: $@" 1>&2

nm $@ 2>&1 | sed -E 's/(ft_nm|nm):/PROGRAM:/g' >/tmp/nm.hex.output
nm_exit=$?

./ft_nm $@ 2>&1 | sed -E 's/(ft_nm|nm):/PROGRAM:/g' >/tmp/ft_nm.hex.output
ft_nm_exit=$?

#if ! diff --color --side-by-side /tmp/ft_nm.anonimized.output /tmp/nm.anonimized.output; then
if ! diff -W $(tput cols) --color --side-by-side --suppress-common-lines /tmp/ft_nm.hex.output /tmp/nm.hex.output; then
	echo DIFF
	exit 1
fi

if ! test "$nm_exit" = "$ft_nm_exit"; then
	echo EXIT "$nm_exit" != "$ft_nm_exit"
	exit 1
fi
