require "rails_helper"

RSpec.describe ChannelController, type: :controller do
  login_user

  before do
    post(
      :create,
      params: {
        :name => "hello",
        :visibility => "public",
      },
    )
  end

  it "returns the channel's id" do
    expect(JSON.parse(response.body)["id"]).to_not(eq(nil))
  end

  it "returns the channel's name" do
    expect(JSON.parse(response.body)["name"]).to(eq("hello"))
  end

  it "returns the channel's visibility" do
    expect(JSON.parse(response.body)["visibility"]).to(eq("public"))
  end

  it "returns the channel's owner" do
    expect(JSON.parse(response.body)["owner"]).to_not(eq(nil))
  end

  it "returns the same channel's owner's id" do
    expect(JSON.parse(response.body)["owner"]["id"]).to(eq(subject.current_user.id))
  end

  it "returns the same channel's owner's username" do
    expect(JSON.parse(response.body)["owner"]["username"]).to(eq(subject.current_user.username))
  end

  it "returns a created status" do
    expect(response).to(have_http_status(:created))
  end
end
