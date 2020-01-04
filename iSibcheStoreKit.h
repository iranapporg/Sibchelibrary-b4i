#import <Foundation/Foundation.h>
#import "iCore.h"
#import <SibcheStoreKit/SibcheStoreKit.h>

//~dependson:SibcheStoreKit.swift.framework.3
//~shortname:SibcheStoreKit
//~version:1.00
//~author: Brandsum
//~event:AllPackageListArrived (PackageList as List)
//~event:PackageInfoArrived (Package as SibchePackage)
//~event:PackagePurchased (Package as SibchePurchasePackage)
//~event:ActivePackageListArrived (PackageList as List)
//~event:LoginSuccess (UserName as String, UserID as String)
//~event:LogoutSuccess
//~event:UserDataArrived (Status as String, UserPhone as String, UserID as String)
@interface iSibcheStoreKit : NSObject
/**
 *Initializes the developer kit implementation code inside the Application_Start function
 *ApiKey - The program key taken from the Apple Developer Panel
 *Scheme - Add a Scheme specific to your app
 */
- (void)Initialize:(B4I *)bi :(NSString*)EventName :(NSString *)ApiKey :(NSString *)Scheme;
/**
 * Allow the developer kit to call the url. Should be called from Application_OpenUrl.
 */
- (void)OpenURL:(NSString *)url :(NSObject *)data :(NSString *)SourceApplication;
/**
 * After you set up the app, you can see the packages you can buy.
 * In response, if successful, the AllPackageListArrived event will be raised with the list of packages that can be purchased.
 * These packages are of the type SibchePackage.
 * If the request fails, the Error event will be raised with the error.
 */
- (void) FetchAllInAppPurchasePackage;
/**
 * Get information about the package by having the package ID or bundle code you want.
 * In response, if successful, the PackageInfoArrived event will be raised with the package info in the form of a SibchePackage (depending on the package).
 * If the request fails, the Error event will be raised with the error.
 */
- (void) FetchInAppPurchasePackage:(NSString *) packageID;
/**
 * After getting the packages list, you can request to buy these packages via the developer kit facebook code.
 * Next, the developer kit will log in if needed and track the payment process.
 * It will then inform you of the success or failure of the purchase.
 * If successful, the PackagePurchased  event will be raised with the package info in the form of a SibchePurchasePackage.
 * If the request fails, the Error event will be raised with the error.
 */
- (void) PurchasePackage:(NSString *) packageID;
/**
 * Get a list of active (purchased) user packages.
 * In response, if successful, the ActivePackageListArrived event will be raised with the list of active purchased packages.
 * Note that this array is an array of type SibchePurchasePackage.
 * If the request fails, the Error event will be raised with the error.
 *
 * Active packages are packages that have been purchased and have not yet been used or that their expiration date has not expired.
 * The definition of apples for active packages for each type of package is as follows:
 * SibcheConsumablePackage : SibcheConsumablePackage purchased but not yet consumed.
 * SibcheNonConsumablePackage : SibcheNonConsumablePackage purchased. Because these packages are one-time purchases, they are active for life when purchased.
 * SibcheSubscriptionPackage : SibcheSubscriptionPackage that have been purchased but have yet to expire.
*/
- (void) FetchActiveInAppPurchasePackages;
/**
 * Consume consumable packages
 * If you want to use usable packages on the client side (within the game / application itself), you should use this method.
 * If successful, it means that the package is successfully consumed and if it fails, we have trouble consuming the package.
 * If the request fails, the Error event will be raised with the error.
*/
- (void) ConsumePurchasePackage:(NSString *)purchasePackageId;
/**
 * Request User Login to Apple Developer Kit
 * We recommend not using this section manually because in the payment process, if the user is not logged in, their apple library will log on to the user.
 *
 * In response, if successful, the LoginSuccess event will be raised with the username and ID of the user.
 * If the request fails, the Error event will be raised with the error.
*/
- (void) LoginUser;
/**
 * Log out the current logged-in user from the Developer Kit and erase all session information.
 * We strongly recommend using this function when the user presses the Purchase Recovery button and requests his Purchase Recovery.
 *
 * The LogoutSuccess event will be raised.
*/
- (void) LogoutUser;
/**
 * Get current user's phone number and userId
 * In response, if successful, the UserDataArrived event will be raised with the user's phone number, user id and login status.
 * If it is logged in, its ‍login status will be 'IsLoggedIn‍‍'.
 * If not logged in, its ‍login status will be 'IsLoggedOut'.
 * If the operation is unsuccessful and the status of the user's logon not know its ‍login status will be 'HaveTokenButFailedToCheck'.
 * If the request fails, the Error event will be raised with the error.
*/
- (void) GetCurrentUserData;
@end

//~shortName:SibcheError
//~ObjectWrapper:SibcheError*
@interface B4ISibcheError : B4IObjectWrapper
//This is the same error number as created in the following table
//
//1000    Unknown error
//1001    This package has already been purchased
//1002    User discontinued operation
//1003    We are having trouble logging in
//1004    The application was not initiated correctly
@property (nonatomic, readonly) long errorCode;
//This is the same http error number that the server responded to.
@property (nonatomic, readonly) long statusCode;
//There is an error message received from the server
@property (nonatomic, readonly) NSString *message;
@end
//~shortName:SibchePackage
//~ObjectWrapper:SibchePackage*
@interface B4ISibchePackage : B4IObjectWrapper
@property (nonatomic, readonly) NSString *packageId;
@property (nonatomic, readonly) NSString *type;
@property (nonatomic, readonly) NSString *code;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *packageDescription;
@property (nonatomic, readonly) double price;
@property (nonatomic, readonly) double totalPrice;
@property (nonatomic, readonly) double discount;
@end
//~shortName:SibcheSubscriptionPackage
//~ObjectWrapper:SibcheSubscriptionPackage*
@interface B4ISibcheSubscriptionPackage : B4IObjectWrapper
@property (nonatomic, readonly) NSString *packageId;
@property (nonatomic, readonly) NSString *type;
@property (nonatomic, readonly) NSString *code;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *packageDescription;
@property (nonatomic, readonly) double price;
@property (nonatomic, readonly) double totalPrice;
@property (nonatomic, readonly) double discount;
@property (nonatomic, readonly) NSString *group;
@property (nonatomic, readonly) double duration;
@end
//~shortName:SibchePurchasePackage
//~ObjectWrapper:SibchePurchasePackage*
@interface B4ISibchePurchasePackage : B4IObjectWrapper
@property (nonatomic, readonly) NSString *purchasePackageId;
@property (nonatomic, readonly) NSString *type;
@property (nonatomic, readonly) NSString *code;
@property (nonatomic, readonly) long long expireAt;
@property (nonatomic, readonly) long long createdAt;
@property (nonatomic, readonly) B4ISibchePackage *package;
@end
