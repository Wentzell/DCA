
import commands
import os
import sys
import time

import matplotlib
matplotlib.use('Agg')

import shutil
import os

import h5py

from pylab import *

import numpy as np
import scipy
from scipy.interpolate import Rbf
import matplotlib.pyplot as plt
from matplotlib import cm

import json
import pylab
import numpy

from pylab import *
from scipy import *

from scipy          import optimize
from scipy.optimize import curve_fit


FIGURE_EXTENSION = ".png"

def plot_imag_w_function(function_name, domains, function_ED, function_QMC):

    dir_name = "pictures"

    if os.path.exists('./'+dir_name+'/' + function_name):
        shutil.rmtree('./'+dir_name+'/' + function_name)
    os.makedirs('./'+dir_name+'/' + function_name)

    freq_dmn = domains["frequency-domain"]["elements"][:]

    shape = function_ED["data"].shape

    figure(num=None)
    for k_ind in range(0, shape[1]):

        x0 = len(freq_dmn)/2-32
        x1 = len(freq_dmn)/2+32
                
        subplot(211)
        plot(freq_dmn[x0:x1], function_QMC["data"][x0:x1,k_ind, 0,0, 0,0, 0], 'ko-', label="Re[ "+function_name+" ]")
        plot(freq_dmn[x0:x1], function_ED ["data"][x0:x1,k_ind, 0,0, 0,0, 0], 'r.', label="Re[ "+function_name+" ]")
            
        subplot(212)
        plot(freq_dmn[x0:x1], function_ED ["data"][x0:x1,k_ind, 0,0, 0,0, 1], 'bo-', label="Re[ "+function_name+" ]")
        plot(freq_dmn[x0:x1], function_QMC["data"][x0:x1,k_ind, 0,0, 0,0, 1], 'g.-', label="Re[ "+function_name+" ]")

    savefig('./'+dir_name+'/' + function_name + '/0_overview' + FIGURE_EXTENSION)

    #figure(num=None)

    diff_re = []
    diff_im = []
    for k_ind in range(0, shape[1]):

        x0 = len(freq_dmn)/2-32
        x1 = len(freq_dmn)/2+32
                
        tmp_re = function_QMC["data"][x0:x1,k_ind, 0,0, 0,0, 0]-function_ED ["data"][x0:x1,k_ind, 0,0, 0,0, 0]
        tmp_im = function_QMC["data"][x0:x1,k_ind, 0,0, 0,0, 1]-function_ED ["data"][x0:x1,k_ind, 0,0, 0,0, 1]

        diff_re.append(tmp_re)
        diff_im.append(tmp_im)

    #savefig('./'+dir_name+'/' + function_name + '/0_overview' + FIGURE_EXTENSION)

    for k_ind in range(0, shape[1]):
        
        figure(num=None)

        x0 = len(freq_dmn)/2-32
        x1 = len(freq_dmn)/2+32
        
        subplot(211)
        plot(freq_dmn[x0:x1], function_QMC["data"][x0:x1,k_ind, 0,0, 0,0, 0], 'ko-', label="Re[ "+function_name+" ]")
        plot(freq_dmn[x0:x1], function_ED ["data"][x0:x1,k_ind, 0,0, 0,0, 0], 'r.', label="Re[ "+function_name+" ]")
            
        subplot(212)
        plot(freq_dmn[x0:x1], function_ED ["data"][x0:x1,k_ind, 0,0, 0,0, 1], 'bo-', label="Re[ "+function_name+" ]")
        plot(freq_dmn[x0:x1], function_QMC["data"][x0:x1,k_ind, 0,0, 0,0, 1], 'g.-', label="Re[ "+function_name+" ]")

        savefig('./'+dir_name+'/' + function_name + '/' + function_name + '_k='+ str(k_ind) + FIGURE_EXTENSION)


filename_ED  = "output__ED.hdf5" #raw_input("ED  filename : ")
filename_QMC = "output_QMC.hdf5" #raw_input("QMC filename : ")

data_ED  = h5py.File(filename_ED ,'r')
data_QMC = h5py.File(filename_QMC,'r')

data_domains = data_ED["domains"]

for i in range(0, len(data_domains.keys())):

    key_name = data_domains.keys()[i]

    print key_name

for i in range(0, len(data_ED.keys())):

    key_name = data_ED.keys()[i]

    print key_name

    if(key_name == "functions"          or 
       key_name == "DCA-loop-functions" or 
       key_name == "CPE-functions"      or 
       key_name == "spectral-functions" or
       key_name == "analysis-functions"):

#         data_functions_ED  = data_ED [key_name]
#         data_functions_QMC = data_QMC[key_name]

        for j in range(0, len(data_ED[key_name].keys())):
        
            function_name = data_ED[key_name].keys()[j]

            print '\tplot '+ function_name + " ... ? "
                
            if(function_name == "Self_Energy"):

                data_function_ED  = data_ED [key_name][function_name]
                data_function_QMC = data_QMC[key_name][function_name]

                plot_imag_w_function(function_name, data_domains, data_function_ED, data_function_QMC)
                    
data_ED.close()
data_QMC.close()
            