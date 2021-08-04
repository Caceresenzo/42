import { Service } from "typedi";
import * as http from "http";
import * as https from "https";
import * as crypto from "crypto";
import * as fs from "fs";
import * as fsExtra from "fs-extra";
import * as path from "path";
import * as fileType from "file-type";
import { URL } from "url";
import fileUpload = require("express-fileupload");

@Service()
export default class AvatarService {
  baseDirectory: string;

  constructor() {
    this.baseDirectory = "data/pictures";
  }

  async download(url: string): Promise<string> {
    const hash = this.generateRandomFileName();
    const dest = this.getDestination(hash);

    return new Promise((resolve, reject) => {
      const file = fs.createWriteStream(dest, { flags: "wx" });

      const request = this.getHttpClient(url).get(url, (response) => {
        if (response.statusCode === 200) {
          response.pipe(file);
        } else {
          file.close();
          fs.unlink(dest, () => {});

          reject(
            `Server responded with ${response.statusCode}: ${response.statusMessage}`
          );
        }
      });

      request.setTimeout(12000, function () {
        request.abort();
      });

      request.on("error", (err) => {
        file.close();
        fs.unlink(dest, () => {});

        reject(err.message);
      });

      file.on("finish", () => {
        resolve(hash);
      });

      file.on("error", (err) => {
        file.close();

        if (err.code === "EEXIST") {
          reject("File already exists");
        } else {
          fs.unlink(dest, () => {});

          reject(err.message);
        }
      });
    });
  }

  async store(
    image: fileUpload.UploadedFile,
    oldHash: string
  ): Promise<string> {
    const hash = this.generateRandomFileName();
    const dest = this.getDestination(hash);

    const oldDest = this.getDestination(oldHash);

    return new Promise(async (resolve, reject) => {
      try {
        const type = await fileType.fromBuffer(image.data);
        if (!type) {
          throw new Error("unknown file type");
        }
        
        if (!type.mime.startsWith("image/")) {
          throw new Error("not an image");
        }

        await image.mv(dest);

        fs.unlink(oldDest, (err) =>
          console.log(`Could not delete old file: ${err}`)
        );

        resolve(hash);
      } catch (error) {
        reject(error);
      }
    });
  }

  generateRandomFileName(): string {
    return crypto.randomBytes(20).toString("hex");
  }

  getHttpClient(rawUrl: string) {
    const url = new URL(rawUrl);

    if (url.protocol == "https:") {
      return https;
    } else {
      return http;
    }
  }

  getDestination(hash: string) {
    return `${this.baseDirectory}/${hash}`;
  }

  async install() {
    fsExtra.ensureDirSync(this.baseDirectory);
  }
}
