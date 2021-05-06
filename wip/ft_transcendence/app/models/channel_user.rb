class ChannelUser < ApplicationRecord
  belongs_to :user
  belongs_to :channel

  validates :user, presence: true
  validates :channel, presence: true
end
