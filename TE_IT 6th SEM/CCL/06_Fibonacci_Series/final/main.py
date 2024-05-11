def fib(n):
	if n<=1:
		return n
	return fib(n-1) + fib(n-2)

for i in range(0,9):
	print(str(fib(i))+" * ")
	

'''
import webapp2

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.headers["Content-Type"] = "text/plain"

        def fib(n):
            if n == 0:
                self.response.out.write("index " + str(n) + " => " + str(0) + "\n")
            if n == 1:
                self.response.out.write("index " + str(n) + " => " + str(1) + "\n")

            a = 0
            b = 1
            c = 0

            for i in range(2, n):
            	self.response.out.write("index " + str(i+1) + " => " + str(c) + "\n")
                c = a + b
                a = b
                b = c

                #self.response.out.write(str(c) + " ")
	
	self.response.out.write("Fibonnaci Series till 8 => \n\n")
        fib(8)

app = webapp2.WSGIApplication([("/", MainPage)], debug=True)
'''
