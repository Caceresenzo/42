# frozen_string_literal: true

class CreateUsers < ActiveRecord::Migration[6.1]
  def change
    create_table :users, id: :uuid do |t|
      t.string :email, null: false
      t.string :username, null: false

      t.boolean :admin, null: false, default: false

      t.string :provider
      t.string :uid

      t.boolean :otp, null: false, default: false
      t.string :otp_secret_key

      t.timestamps
    end

    add_index :users, :email, unique: true
    add_index :users, :username, unique: true
    add_index :users, :provider
    add_index :users, :uid
  end
end
