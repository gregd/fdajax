class User < ActiveRecord::Base

  validates_inclusion_of :login_state, :in => ["in","out"], :allow_nil => true

  def self.authenticate(name, password)
    user = self.find_by_name(name)
    if user
      if user.password != password
        user = nil
      else
        user.login_state = "in"
        user.save
        user
      end
    end
  end

  def self.logout(user_id)
    if user = self.find_by_id(user_id)
      user.login_state = "out"
      user.save
    end
  end

end
