import webapp2

class MainPage(webapp2.RequestHandler):
	def get(self):
		self.response.headers["Content-Type"]="text/plain"
		for i in range(1,11):
			self.response.out.write("10 * "+ str(i) + " = " + str(i*10) +"\n")

app=webapp2.WSGIApplication([("/",MainPage)],debug=True)
