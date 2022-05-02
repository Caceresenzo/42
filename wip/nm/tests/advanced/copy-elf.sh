PROJECT=$1

FILES=$(echo /tmp/$PROJECT/files)
TMP_DIR=$(echo /tmp/$PROJECT/*/)
LOCAL_TMP_DIR=$(echo $PROJECT)_tmp

rm -rf $LOCAL_TMP_DIR
mkdir $LOCAL_TMP_DIR

(cd $TMP_DIR && find . -exec file {} \; | grep ELF | awk -F: '{ print $1 }' > $FILES)
rsync -Pva --files-from=$FILES $TMP_DIR/ $LOCAL_TMP_DIR/

mv $LOCAL_TMP_DIR $PROJECT