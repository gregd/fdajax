class MinichatController < ApplicationController
  before_filter :authorize, :only => [:index, :new_message, :logout]

  def login
    session[:user_id] = nil
    if request.post?
      user = User.authenticate(params[:name], params[:password])
      if user
        session[:user_id] = user.id
        cmd = "cmd=login&user_id=" + user.id.to_s + "&sess_id=" + session.session_id + "&ip_addr=" + request.remote_ip
        logger.info Net::HTTP.get_response('127.0.0.1', '/live.fdajax?' + cmd, 3000).body
        redirect_to(:action => "index" )
      else
        flash[:notice] = "Invalid user/password combination"
      end
    end
  end

  def logout
    cmd = "cmd=logout&user_id=" + session[:user_id].to_s
    logger.info Net::HTTP.get_response('127.0.0.1', '/live.fdajax?' + cmd, 3000).body
    User.logout(session[:user_id])
    session[:user_id] = nil
    flash[:notice] = "Logged out"
    redirect_to("/")
  end

  def index
    @created = Time.now
    @user = User.find(session[:user_id])
    @others = User.find(:all, :conditions => ["login_state = 'in' AND id != ? ", @user.id]).map {|u| u.name }
  end

  def new_message
    @user = User.find(session[:user_id])
    @new_message = params[:message]

    respond_to do |wants|
      wants.js do
        render :update do |page|
          page.insert_html :bottom, "chat_output", :partial => "new_message"
          page << "$('chat_output').scrollTop = $('chat_output').scrollHeight;"
          page << "Field.clear('message');"
          page << "Field.focus('message');"
        end
      end
    end

    User.find(:all, :conditions => ["login_state = 'in' AND id != ? ", @user.id]).each do |peer|
      cmd = "cmd=push&types=chat&peer_id=" + peer.id.to_s + "&mes=" + CGI::escape(response.body)
      logger.info Net::HTTP.get_response('127.0.0.1', '/live.fdajax?' + cmd, 3000).body
    end
  end

  private
  def authorize
    unless User.find_by_id(session[:user_id])
      flash[:notice] = "Please log in"
      redirect_to(:action => "login" )
    end
  end

end
