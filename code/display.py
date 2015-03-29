from pylab import *

data = loadtxt('counts.txt')
sample = atleast_2d(loadtxt('posterior_sample.txt'))
n = (sample.shape[1] - 1)//2

hist(sample[:,0], 100)
xlabel('Thickness')
show()


ion()
hold(False)
for i in xrange(0, sample.shape[0]):
  subplot(2,1,1)
  hold(False)
  plot(sample[:,1:(n+1)].mean(axis=0), 'ro-')
  hold(True)
  plot(sample[i, 1:(n+1)], 'bo-')
  ylim([0, 1])

  subplot(2,1,2)
  hold(False)
  plot(sample[i, (n+1):], 'ro-')
  hold(True)
  plot(data, 'bo-')
  draw()

ioff()
show()

