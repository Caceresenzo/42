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

    get(
      :show,
      params: {
        :id => JSON.parse(response.body)["id"],
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

  it "returns the channel's members" do
    expect(JSON.parse(response.body)["members"]).to_not(eq(nil))
  end

  it "returns the channel's owner as a member (id)" do
    expect(JSON.parse(response.body)["members"][0]["user"]["id"]).to(eq(subject.current_user.id))
  end

  it "returns the channel's owner as a member (username)" do
    expect(JSON.parse(response.body)["members"][0]["user"]["username"]).to(eq(subject.current_user.username))
  end

  it "returns the channel's owner as an admin member" do
    expect(JSON.parse(response.body)["members"][0]["admin"]).to(eq(true))
  end

  it "returns the channel's owner as a not banned member" do
    expect(JSON.parse(response.body)["members"][0]["banned"]).to(eq(false))
  end

  it "returns a ok status" do
    expect(response).to(have_http_status(:ok))
  end
end
