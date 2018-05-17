#!/usr/bin/bash
currentdir=$(pwd)
inputdir=$1

for a in $(ls $1); do
  cd ${inputdir}/${a}/;
  outdir=${inputdir}/$(echo ${a} | sed "s/_XYZ\..*$//g")
  #echo $outdir
  mkdir -p ${outdir}
  for tarball in $(ls .); do
    if [[ ${tarball} == *.tgz ]]; then
      tar -xzvf ${tarball} -C ${outdir};
    fi
  done
done

cd ${currentdir}
