OUTDIR=${PWD}/${NAME}
CNTDIR=content

.PHONEY: all jb build fixlinks images pub clean

all: build

jb:
	# -v verbose
	# -all re-build all pages not just changed pages
	# -W make warning treated as errors
	# -n nitpick generate warnings for all missing links
	# --keep-going despite -W don't stop delay errors till the end
	jupyter-book build -v --all -n --keep-going --path-output ${OUTDIR} --config ${PWD}/${CNTDIR}/${SN}_config.yml --toc ${PWD}/${CNTDIR}/${SN}_toc.yml ${CNTDIR}

images: jb
	-mkdir -p ${OUTDIR}/_build/html/images
	cp -r ${CNTDIR}/images/* ${OUTDIR}/_build/html/images

fixlinks: images
	./fixlinks.sh ${OUTDIR}/_build/html

build: fixlinks

pub:
	ghp-import -n -p --prefix=${NAME} -f ${OUTDIR}/_build/html
	@./ghp-nojekyll.sh
	@echo "Published to:"
	@./ghp-url.sh ${NAME}

clean: 
	${RM} -r  ${OUTDIR}
