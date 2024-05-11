import webapp2

class MainPage(webapp2.RequestHandler):
	def get(self):
		self.response.headers["Content-Type"]="text/plain"
		
		for i in range(1,11):
			self.response.out.write("5 * ")
			self.response.out.write(str(i)+" =")
			self.response.out.write(" "+str(i*5)+"\n")
		self.response.out.write("\n\nTable has been printed!!")
			
			
app=webapp2.WSGIApplication([("/",MainPage)],debug=True)
# Web Server Gateway Interface
