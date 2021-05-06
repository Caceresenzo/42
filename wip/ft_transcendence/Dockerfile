FROM ruby:2.5.1

RUN curl https://deb.nodesource.com/setup_12.x | bash
RUN curl https://dl.yarnpkg.com/debian/pubkey.gpg | apt-key add -
RUN echo "deb https://dl.yarnpkg.com/debian/ stable main" | tee /etc/apt/sources.list.d/yarn.list

RUN apt-get update && apt-get install -y nodejs yarn postgresql-client
RUN apt-get install -y zsh git nano vim curl wget
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
# for postgres
RUN apt-get install -y libpq-dev

WORKDIR /myapp
# COPY Gemfile /myapp/Gemfile
# COPY Gemfile.lock /myapp/Gemfile.lock

# RUN bundle install
# COPY package.json yarn.lock /myapp/

# COPY . /myapp

EXPOSE 3000

CMD zsh
# CMD ["rails", "s", "-b", "0.0.0.0"]