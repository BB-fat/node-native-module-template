const fs = require('fs');
const path = require('path');

function searchFiles(dir, ext) {
  const result = [];
  const items = fs.readdirSync(dir);
  items.forEach((item) => {
    const file = path.join(dir, item);
    const stat = fs.statSync(file);
    if (stat.isFile() && ext.indexOf(path.extname(file).slice(1)) >= 0) {
      result.push(file);
    } else if (stat.isDirectory()) {
      result.push(...searchFiles(file, ext));
    }
  });
  return result;
}

const config = JSON.parse(fs.readFileSync(path.join('tools', 'bindings.json'), { encoding: 'utf-8' }));

// 跨平台源文件
config.targets[0].sources = [path.join('src', 'export.cc'), ...searchFiles('src/common', ['cpp', 'cc'])];

const { conditions } = config.targets[0];
const getPlatformConfig = (platform) => conditions.find((e) => e[0].indexOf(platform) >= 0);

// mac源文件
getPlatformConfig('mac')[1].sources = searchFiles(path.join('src', 'mac'), ['cc', 'mm']);

// windows源文件
getPlatformConfig('win')[1].sources = searchFiles(path.join('src', 'windows'), ['cc', 'cpp']);

fs.writeFileSync('binding.gyp', JSON.stringify(config));
