import webapp2

class MainPage(webapp2.RequestHandler):
	def get(self):
		self.response.out.write("Final prac done")

app=webapp2.WSGIApplication([("/",MainPage)],debug=True)

# WSGI => WEB SERVER GATEWAY INTERFACE
