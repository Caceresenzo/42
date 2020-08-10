for f in *.bf; do
	cat $f | tr '><+.,[]' 'DdIOo{}' | tr '-' 'i' > $(basename -- "$f" .bf).mo
done
