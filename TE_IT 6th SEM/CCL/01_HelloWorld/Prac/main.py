import webapp2

class MainPage(webapp2.RequestHandler) :
	def get(self):
		self.response.out.write("31 111 53")

app=webapp2.WSGIApplication([("/",MainPage),debug=True])
	
