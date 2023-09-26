# Upgrade project SPFx.LifeScienceWebPart to v1.18.0

Date: 26/09/2023

## Findings

Following is the list of steps required to upgrade your project to SharePoint Framework version 1.18.0. [Summary](#Summary) of the modifications is included at the end of the report.

### FN001001 @microsoft/sp-core-library | Required

Upgrade SharePoint Framework dependency package @microsoft/sp-core-library

Execute the following command:

```sh
npm i -SE @microsoft/sp-core-library@1.18.0
```

File: [./package.json:21:5](./package.json)

### FN001002 @microsoft/sp-lodash-subset | Required

Upgrade SharePoint Framework dependency package @microsoft/sp-lodash-subset

Execute the following command:

```sh
npm i -SE @microsoft/sp-lodash-subset@1.18.0
```

File: [./package.json:22:5](./package.json)

### FN001003 @microsoft/sp-office-ui-fabric-core | Required

Upgrade SharePoint Framework dependency package @microsoft/sp-office-ui-fabric-core

Execute the following command:

```sh
npm i -SE @microsoft/sp-office-ui-fabric-core@1.18.0
```

File: [./package.json:23:5](./package.json)

### FN001004 @microsoft/sp-webpart-base | Required

Upgrade SharePoint Framework dependency package @microsoft/sp-webpart-base

Execute the following command:

```sh
npm i -SE @microsoft/sp-webpart-base@1.18.0
```

File: [./package.json:25:5](./package.json)

### FN001021 @microsoft/sp-property-pane | Required

Upgrade SharePoint Framework dependency package @microsoft/sp-property-pane

Execute the following command:

```sh
npm i -SE @microsoft/sp-property-pane@1.18.0
```

File: [./package.json:24:5](./package.json)

### FN001022 office-ui-fabric-react | Required

Remove SharePoint Framework dependency package office-ui-fabric-react

Execute the following command:

```sh
npm un -S office-ui-fabric-react
```

File: [./package.json:28:5](./package.json)

### FN001035 @fluentui/react | Required

Upgrade SharePoint Framework dependency package @fluentui/react

Execute the following command:

```sh
npm i -SE @fluentui/react@8.106.4
```

File: [./package.json:17:5](./package.json)

### FN001034 @microsoft/sp-adaptive-card-extension-base | Optional

Install SharePoint Framework dependency package @microsoft/sp-adaptive-card-extension-base

Execute the following command:

```sh
npm i -SE @microsoft/sp-adaptive-card-extension-base@1.18.0
```

File: [./package.json:15:3](./package.json)

### FN002001 @microsoft/sp-build-web | Required

Upgrade SharePoint Framework dev dependency package @microsoft/sp-build-web

Execute the following command:

```sh
npm i -DE @microsoft/sp-build-web@1.18.0
```

File: [./package.json:39:5](./package.json)

### FN002002 @microsoft/sp-module-interfaces | Required

Upgrade SharePoint Framework dev dependency package @microsoft/sp-module-interfaces

Execute the following command:

```sh
npm i -DE @microsoft/sp-module-interfaces@1.18.0
```

File: [./package.json:40:5](./package.json)

### FN002022 @microsoft/eslint-plugin-spfx | Required

Upgrade SharePoint Framework dev dependency package @microsoft/eslint-plugin-spfx

Execute the following command:

```sh
npm i -DE @microsoft/eslint-plugin-spfx@1.18.0
```

File: [./package.json:37:5](./package.json)

### FN002023 @microsoft/eslint-config-spfx | Required

Upgrade SharePoint Framework dev dependency package @microsoft/eslint-config-spfx

Execute the following command:

```sh
npm i -DE @microsoft/eslint-config-spfx@1.18.0
```

File: [./package.json:36:5](./package.json)

### FN002026 typescript | Required

Upgrade SharePoint Framework dev dependency package typescript

Execute the following command:

```sh
npm i -DE typescript@4.7.4
```

File: [./package.json:49:5](./package.json)

### FN002028 @microsoft/rush-stack-compiler-4.7 | Required

Install SharePoint Framework dev dependency package @microsoft/rush-stack-compiler-4.7

Execute the following command:

```sh
npm i -DE @microsoft/rush-stack-compiler-4.7@0.1.0
```

File: [./package.json:35:3](./package.json)

### FN010001 .yo-rc.json version | Recommended

Update version in .yo-rc.json

```json
{
  "@microsoft/generator-sharepoint": {
    "version": "1.18.0"
  }
}
```

File: [./.yo-rc.json:10:5](./.yo-rc.json)

### FN010010 .yo-rc.json @microsoft/teams-js SDK version | Recommended

Update @microsoft/teams-js SDK version in .yo-rc.json

```json
{
  "@microsoft/generator-sharepoint": {
    "sdkVersions": {
      "@microsoft/teams-js": "2.12.0"
    }
  }
}
```

File: [./.yo-rc.json:2:3](./.yo-rc.json)

### FN012017 tsconfig.json extends property | Required

Update tsconfig.json extends property

```json
{
  "extends": "./node_modules/@microsoft/rush-stack-compiler-4.7/includes/tsconfig-web.json"
}
```

File: [./tsconfig.json:2:3](./tsconfig.json)

### FN021003 package.json engines.node | Required

Update package.json engines.node property

```json
{
  "engines": {
    "node": ">=16.13.0 <17.0.0 || >=18.17.1 <19.0.0"
  }
}
```

File: [./package.json:6:5](./package.json)

### FN002024 eslint | Required

Install SharePoint Framework dev dependency package eslint

Execute the following command:

```sh
npm i -DE eslint@8.7.0
```

File: [./package.json:35:3](./package.json)

### FN007002 serve.json initialPage | Required

Update serve.json initialPage URL

```json
{
  "initialPage": "https://{tenantDomain}/_layouts/workbench.aspx"
}
```

File: [./config/serve.json:5:3](./config/serve.json)

### FN014008 Hosted workbench type in .vscode/launch.json | Recommended

In the .vscode/launch.json file, update the type property for the hosted workbench launch configuration

```json
{
  "configurations": [
    {
      "type": "edge"
    }
  ]
}
```

File: [.vscode\launch.json:8:7](.vscode\launch.json)

### FN014009 Hosted workbench URL in .vscode/launch.json | Recommended

In the .vscode/launch.json file, update the url property for the hosted workbench launch configuration

```json
{
  "configurations": [
    {
      "url": "https://{tenantDomain}/_layouts/workbench.aspx"
    }
  ]
}
```

File: [.vscode\launch.json:8:7](.vscode\launch.json)

### FN017001 Run npm dedupe | Optional

If, after upgrading npm packages, when building the project you have errors similar to: "error TS2345: Argument of type 'SPHttpClientConfiguration' is not assignable to parameter of type 'SPHttpClientConfiguration'", try running 'npm dedupe' to cleanup npm packages.

Execute the following command:

```sh
npm dedupe
```

File: [./package.json](./package.json)

## Summary

### Execute script

```sh
npm un -S office-ui-fabric-react
npm i -SE @microsoft/sp-core-library@1.18.0 @microsoft/sp-lodash-subset@1.18.0 @microsoft/sp-office-ui-fabric-core@1.18.0 @microsoft/sp-webpart-base@1.18.0 @microsoft/sp-property-pane@1.18.0 @fluentui/react@8.106.4 @microsoft/sp-adaptive-card-extension-base@1.18.0
npm i -DE @microsoft/sp-build-web@1.18.0 @microsoft/sp-module-interfaces@1.18.0 @microsoft/eslint-plugin-spfx@1.18.0 @microsoft/eslint-config-spfx@1.18.0 typescript@4.7.4 @microsoft/rush-stack-compiler-4.7@0.1.0 eslint@8.7.0
npm dedupe
```

### Modify files

#### [./.yo-rc.json](./.yo-rc.json)

Update version in .yo-rc.json:

```json
{
  "@microsoft/generator-sharepoint": {
    "version": "1.18.0"
  }
}
```

Update @microsoft/teams-js SDK version in .yo-rc.json:

```json
{
  "@microsoft/generator-sharepoint": {
    "sdkVersions": {
      "@microsoft/teams-js": "2.12.0"
    }
  }
}
```

#### [./tsconfig.json](./tsconfig.json)

Update tsconfig.json extends property:

```json
{
  "extends": "./node_modules/@microsoft/rush-stack-compiler-4.7/includes/tsconfig-web.json"
}
```

#### [./package.json](./package.json)

Update package.json engines.node property:

```json
{
  "engines": {
    "node": ">=16.13.0 <17.0.0 || >=18.17.1 <19.0.0"
  }
}
```

#### [./config/serve.json](./config/serve.json)

Update serve.json initialPage URL:

```json
{
  "initialPage": "https://{tenantDomain}/_layouts/workbench.aspx"
}
```

#### [.vscode\launch.json](.vscode\launch.json)

In the .vscode/launch.json file, update the type property for the hosted workbench launch configuration:

```json
{
  "configurations": [
    {
      "type": "edge"
    }
  ]
}
```

In the .vscode/launch.json file, update the url property for the hosted workbench launch configuration:

```json
{
  "configurations": [
    {
      "url": "https://{tenantDomain}/_layouts/workbench.aspx"
    }
  ]
}
```
