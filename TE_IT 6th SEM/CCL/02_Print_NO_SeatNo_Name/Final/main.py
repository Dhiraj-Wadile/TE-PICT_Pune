import webapp2

class Pages(webapp2.RequestHandler):
	def get(self):
		self.response.headers["Content-Type"]="text/plain"
		for i in range(5):
			self.response.out.write("Name => SHUBZ  Roll No => 33371  Dept => IT\n")
			
app=webapp2.WSGIApplication([("/",Pages)],debug=True)

#WSGI => Web Server Gateway Interface
