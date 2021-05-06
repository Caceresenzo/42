require "rails_helper"

# RSpec.describe ChannelController, type: :controller do
#   login_user

#   it "should have a current_user" do
#     expect(subject.current_user).to_not eq(nil)
#   end

#   describe "GET channels/" do
#     it "exists and responds" do
#       get :all

#       expect(response.status).to eq(200)
#     end
#   end

#   describe "POST channels/" do
#     it "require name" do
#       post(
#         :create,
#         params: {},
#       )

#       expect(response.status).to(eq(406))
#     end

#     it "require visibility" do
#       post(
#         :create,
#         params: {
#           name: "hello",
#         },
#       )

#       expect(response.status).to(eq(406))
#     end

#     it "require valid visibility" do
#       post(
#         :create,
#         params: {
#           name: "hello",
#           visibility: "world",
#         },
#       )

#       expect(response.status).to(eq(406))
#     end

#     it "require password if visibility is protected" do
#       post(
#         :create,
#         params: {
#           name: "hello",
#           visibility: "protected",
#         },
#       )

#       expect(response.status).to(eq(406))
#     end

#     it "not require password if visibility is not protected" do
#       post(
#         :create,
#         params: {
#           name: "hello",
#           visibility: "public",
#           password: "world",
#         },
#       )

#       expect(response.status).to(eq(406))
#     end

#     it "create" do
#       post(
#         :create,
#         params: {
#           name: "hello",
#           visibility: "public",
#         },
#       )

#       expect(response.status).to(eq(200))
#     end
#   end

#   describe "GET channels/id" do
#     it "exists and responds" do
#       get(
#         :show,
#         params: {
#           id: Channel.first.id,
#         },
#       )

#       expect(response.status).to(eq(200))
#     end
#   end
# end
