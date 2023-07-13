#!/bin/bash

# runs Make and if it succeeds, commits and pushes to github
make && git commit -F - << EOF && git push origin $1