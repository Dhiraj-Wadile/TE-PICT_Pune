import webapp2

class MainPage(webapp2.RequestHandler):
	def get(self):
		self.response.headers["Content-Type"]="text/plain"
		for i in range(5):
			self.response.out.write("Name => shubham   Roll No => 33371   Dept => IT\n")

app=webapp2.WSGIApplication([("/",MainPage)],debug=True)
