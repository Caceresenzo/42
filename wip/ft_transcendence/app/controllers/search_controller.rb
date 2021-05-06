class SearchController < ApplicationController
  before_action :load_query

  # GET /search/users?query=<query>
  def users()
    render({
      json: SearchUserBlueprint.render(find_users(), root: :users),
    })
  end

  # GET /search/channels?query=<query>
  def channels()
    render({
      json: SearchChannelBlueprint.render(find_channels(), root: :channels),
    })
  end

  private

  def load_query()
    @query = params.require(:query).downcase
  end

  def find_users()
    return User.all.where("LOWER(username) LIKE ?", "%#{@query}%")
  end

  def find_channels()
    return Channel.includes(:owner).all.where("LOWER(name) LIKE ?", "%#{@query}%")
  end
end

class SearchUserBlueprint < Blueprinter::Base
  identifier :id

  fields :username
end

class SearchChannelBlueprint < Blueprinter::Base
  identifier :id

  fields :name
  association :owner, blueprint: SearchUserBlueprint
end
