SHELL := /bin/bash
.PHONY: help build pub clean
DIR=$(shell pwd -P)
NAME=$(shell basename ${DIR})

OUTDIR=${DIR}
CNTDIR=content

.PHONY: all jb build fixlinks images pub clean

all: build

jb:
	# -v verbose
	# -all re-build all pages not just changed pages
	# -W make warning treated as errors
	# -n nitpick generate warnings for all missing links
	# --keep-going despite -W don't stop delay errors till the end
	jupyter-book build -v --all -n --keep-going --path-output ${OUTDIR} --config ${PWD}/${CNTDIR}/${NAME}_config.yml --toc ${PWD}/${CNTDIR}/${NAME}_toc.yml ${CNTDIR}

images: jb
	-mkdir -p ${OUTDIR}/_build/html/images
	cp -r ${CNTDIR}/images/* ${OUTDIR}/_build/html/images

fixlinks: images
	./fixlinks.sh ${OUTDIR}/_build/html

build: ## build the book
build: fixlinks

pub:
	ghp-import -n -p --prefix=${NAME} -f ${OUTDIR}/_build/html
	@./ghp-nojekyll.sh
	@echo "Published to:"
	@./ghp-url.sh ${NAME}

clean: 
	${RM} -r  ${OUTDIR}

help:
# http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
	@grep -E '^[a-zA-Z0-9_%/-]+:.*?## .*$$' $(MAKEFILE_LIST) |  awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
