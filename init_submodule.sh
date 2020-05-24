#!/bin/bash

function error()
{
	echo "provide a name"
	exit 1
}

function init()
{
	echo "renaming template make lines to $1"
	upper=$(echo $1 | tr '[:lower:]' '[:upper:]')

	sed -i "s/TEMPLATE/$upper/g" module.mk
	sed -i "s/TEMPLATE/$upper/g" Makefile
	sed -i "s/template/$1/g" Makefile
	sed -i "s/template/$1/g" .gitignore

	echo "creating initial files"
	mkdir src
	touch src/$1.c
	touch src/$1.h

	echo "clearing README"
	echo "# $1" > README.md
}

# do we have a name parameter?
[ $# -eq 1 ] && init $1 || error
rm -- "$0"

# cleaning up
git add .gitignore Makefile README.md module.mk test-$1 src/*
git rm $0
git commit -m "initilised repository"
git push
