FactoryBot.define do
  factory :user do
    email { Faker::Internet.email }
    username { Faker::Internet.username }
    provider { "the-world" }
    uid { Faker::Blockchain::Bitcoin.address } # don't need to be pretty, just unique
  end
end
