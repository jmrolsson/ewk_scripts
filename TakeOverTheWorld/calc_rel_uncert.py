# mass
mass = [300, 325, 350, 375, 400, 425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675, 700, 725, 750, 775, 800]

# cross-section uncertainty [fb]
uncert = [26.3602, 20.0201, 15.4539, 12.0956, 9.61659, 7.73547, 6.2389, 5.05005, 4.16461, 3.46763, 2.88065, 2.40183, 2.04438, 1.70195, 1.43519, 1.21937, 1.04092, 0.885243, 0.769988, 0.654544, 0.564061]

# cross-section [fb]
xsec  =  [386.936, 281.911, 209.439, 158.06, 121.013, 93.771, 73.4361, 58.0811, 46.3533, 37.2636, 30.1656, 24.5798, 20.1372, 16.5706, 13.7303, 11.3975, 9.51032, 7.9595, 6.69356, 5.63562, 4.75843]

# branching ratios for W and h
br_w = 0.6741
br_h = 0.582

# fb to pb
pb = 0.001

print 'mass, xsec [pb], xsec*br_w*br_h [pb], uncertainty [pb], rel uncert (uncert/xsec)'
for i in xrange(len(xsec)):
    print '{:.1f}, {:.6g}, {:.6g}, {:.6g}, {:.6g}'.format(mass[i], xsec[i]*pb, xsec[i]*br_w*br_h*pb, uncert[i]*pb, uncert[i]/xsec[i])
