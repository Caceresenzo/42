# frozen_string_literal: true

class Ability
  include CanCan::Ability

  def initialize(user)
    return unless user

    can :current, User
    can :all, User
    can :show, User

    can :all, Channel
    can :show, Channel do |channel|
      ChannelHelper.can_user_show(channel, user)
    end
    can :create, Channel
    can :transfer_ownership, Channel, :owner_id => user.id
    can :update, Channel, :owner_id => user.id
    can :delete, Channel, :owner_id => user.id
    can :join, Channel
    can :leave, Channel
  end
end
