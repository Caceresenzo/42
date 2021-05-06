class ChannelMessage < ApplicationRecord
  enum content_type: [:text, :invite]

  belongs_to :user
  belongs_to :channel

  validates :user, presence: true
  validates :channel, presence: true
  validates :content, presence: true, length: { minimum: 1, maximum: 100 }
  validate_enum_attributes :content_type
end
