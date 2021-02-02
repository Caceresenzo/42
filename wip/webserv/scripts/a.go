package main

import (
        "fmt"
        "io"
        "io/ioutil"
        "net/url"

        //"github.com/benburkert/http"
        "net/http"
        //"encoding/binary"
        _ "os"
)

const (
        chunk1 = "First Chunk"
        chunk2 = "Second Chunk"
)

func x() {
        rd, wr := io.Pipe()

        u, _ := url.Parse("http://localhost:80/directory/youpla.bla")

        req := &http.Request{
                Method:           "POST",
                ProtoMajor:       1,
                ProtoMinor:       1,
                URL:              u,
                TransferEncoding: []string{"chunked"},
                Body:             rd,
                Header:                         make(map[string][]string),
        }
        req.Header.Set("Content-Type", "plain/text")

        client := http.DefaultClient

        go func() {
                buf := make([]byte, 8000)
                for i := 0; i < 8000; i++ {
                        buf[i] = 'n'
                }

                for i := 0; i < 12500; i++ {
                        wr.Write(buf)
                }

                wr.Close()
        }()

        resp, err := client.Do(req)
        if nil != err {
                fmt.Println("error =>", err.Error())
                return
        }
        defer resp.Body.Close()
        body, err := ioutil.ReadAll(resp.Body)
        if nil != err {
                fmt.Println("error =>", err.Error())
        } else {
                fmt.Println(len(body))
        }
}

func main() {
        x()
        x()
        x()
}
