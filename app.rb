class App < Sinatra::Base
  register Sinatra::Reloader
 
  get '/' do
		cache_control :public
		haml :index
  end

	get '/s.css' do
		scss :s
	end
end
