class Api::BaseException < StandardError
  def message()
    return "no message"
  end

  def status()
    return :internal_server_error
  end
end
