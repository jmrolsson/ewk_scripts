Mapping DID to Group
--------------------

Making the Signals
~~~~~~~~~~~~~~~~~~

Below is an example command that I use to generate the signal portion of the ``did_to_group.json`` file::

  cat <(rucio list-dids --short mc15_13TeV:mc15_13TeV.*.MGPy8EG_A14N_GG_bbn1_*.merge.DAOD_SUSY10.*p2666/ |  cut -d '.' -f 2,3 | tr '.' "\t" | cut -d '_' -f 1,5-7 | sed -e 's/MGPy8EG_//g' | tr '_' "\t" | sort -k2 -n | awk '{print "\""$1"\": \"Gbb_"$2"_"$3"_"$4"\","}') <(rucio list-dids --short mc15_13TeV:mc15_13TeV.*.MGPy8EG_A14N_GG_ttn1*.merge.DAOD_SUSY10.*p2666/ |  cut -d '.' -f 2,3 | tr '.' "\t" | cut -d '_' -f 1,5-7 | sed -e 's/MGPy8EG_//g' | tr '_' "\t" | sort -k2 -n | awk '{print "\""$1"\": \"Gtt_"$2"_"$3"_"$4"\","}') <(rucio list-dids --short mc15_13TeV:mc15_13TeV.*.MGPy8EG_A14N23LO_GG_tb_*.merge.DAOD_SUSY10.*p2666/ |  cut -d '.' -f 2,3 | tr '.' "\t" | cut -d '_' -f 1,5-7 | sed -e 's/MGPy8EG_//g' | tr '_' "\t" | sort -k2 -n | awk '{print "\""$1"\": \"Gtb_"$2"_"$3"_"$4"\","}' )> signal

Explaining it is a little complicated, but the steps are just to split out the mass values and then use ``awk`` to recombine into something that looks like valid json.

Making the Backgrounds
~~~~~~~~~~~~~~~~~~~~~~

The following script will produce the backgrounds::

  rucio list-dids --short user.gstark:user.gstark*tag2.4.19-0-0* | cut -d '.' -f 4,5 | tr '.' "\t" | grep -v Gbb | grep -v Gtt | sort -k2 -n | awk '{print "\""$1"\": \""$2"\","}' | sort -u > bkgd

Making the list of DIDs
~~~~~~~~~~~~~~~~~~~~~~~

For each process, we need a list of DIDs. The best way is to use a loop like so::

  for process in Gbb Gtb Gtt W_sherpa_220 Z_sherpa_220 W_sherpa_221 Z_sherpa_221 diboson dijet singletop singletop_syst topEW ttbar ttbar_afii ttbar_syst; do find /share/t3data3/kratsg/MBJ/HF_tag2.4.24-1-0/*.${process}.* -type d | cut -d '.' -f 5 | sort > ${process}.list; done

Converting to HF from Smearing NTuples
--------------------------------------

The script ``smearing2hf.py`` is made to do this functionality. It's also written in a very generic way. You specify a ``mappings.json`` file that maps input branches to output branches, and then tell the script this mapping file, along with the input treename and the output treename. It will do the rest for you.

.. code::

  python smearing2hf.py test.root --mappings mappings.json --treename nominal_0L --out-treename nominal

