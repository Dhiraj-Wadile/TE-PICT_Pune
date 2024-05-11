import webapp2

class MainPage(webapp2.RequestHandler):
	def get(self):
		self.response.headers["Content-Type"]="text/plain"
		
		i=1
		while i<=10: 
			self.response.out.write("Seat No 1234  Dept => IT\n")
			i+=1

app=webapp2.WSGIApplication([("/",MainPage)],debug=True)		# [ ("/", MainPage ) ]
# Web Server Gateway Interface
