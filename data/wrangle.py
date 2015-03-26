#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division, print_function
import os
import requests
import numpy as np
import pandas as pd
from cStringIO import StringIO


def download_catalog(name):
    fn = "{0}.h5".format(name)
    if os.path.exists(fn):
        return pd.read_hdf(fn, name)
    print("Downloading {0}...".format(name))
    url = ("http://exoplanetarchive.ipac.caltech.edu/cgi-bin/nstedAPI/"
           "nph-nstedAPI?table={0}&select=*").format(name)
    r = requests.get(url)
    if r.status_code != requests.codes.ok:
        r.raise_for_status()
    fh = StringIO(r.content)
    df = pd.read_csv(fh)
    df.to_hdf(fn, name, format="t")
    return df


# Load the catalogs.
kois = download_catalog("cumulative")
stlr = download_catalog("q1_q16_stellar")

# Select the cool stars following Dressing.
cool = (stlr.teff < 4000) & (stlr.logg > 3)
cool_stlr = stlr[cool]

# Select the KOIs that fall into this set.
cool_kois = kois[kois.kepid.isin(cool_stlr.kepid)]

# Only select candidates and confirmed.
cool_kois = cool_kois[cool_kois.koi_pdisposition == "CANDIDATE"]

# Count the multiplicity.
counts = np.array(cool_kois.groupby("kepid").kepoi_name.count())
hist, _ = np.histogram(counts, np.arange(-0.5, counts.max()+1.5))
hist[0] = len(cool_stlr) - hist.sum()

# Save to a file.
with open("counts.txt", "w") as f:
    f.write("\n".join(map("{0}".format, hist)))
